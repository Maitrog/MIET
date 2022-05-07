<?php

namespace Tests\Feature;

use App\Models\Set;
use Tests\TestCase;

class SetTest extends TestCase
{
    public function test_get_all_sets_returns_a_successful_response()
    {
        $response = $this->get('/api/v1/sets');

        $response->assertStatus(200);
    }
    public function test_get_set_by_id_returns_a_successful_response()
    {
        $set = Set::factory()->create();
        $response = $this->get('/api/v1/sets/' . $set->id);

        $data = [
            'data' => [
                'id' => $set->id,
                'exercise_id' => $set->exercise_id,
                'workout_id' => $set->workout_id,
                'quantity' => $set->quantity,
                'time'=> $set->time,
                'distance' => $set->distance,
                'additional_weight' => $set->additional_weight,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_get_set_by_id_returns_a_bad_request_response()
    {
        $response = $this->get('/api/v1/sets/f');
        $response->assertStatus(400);
    }
    public function test_get_set_by_id_returns_a_not_found_response()
    {
        $set = Set::factory()->create();
        $response = $this->get('/api/v1/sets/' . $set->id + 1);
        $response->assertStatus(404);
    }

    public function test_create_set_returns_a_successful_response()
    {
        $set = Set::factory()->raw();
        $response = $this->postJson('/api/v1/sets/', $set);
        $data = [
            'data' => [
                'exercise_id' => $set['exercise_id'],
                'workout_id' => $set['workout_id'],
                'quantity' => $set['quantity'],
                'time'=> $set['time'],
                'distance' => $set['distance'],
                'additional_weight' => $set['additional_weight'],
            ],
        ];
        $response->assertStatus(201)->assertJson($data);
        $this->assertDatabaseHas('sets', $set);
    }

    public function test_update_set_returns_a_successful_response()
    {
        $set = Set::factory()->create();
        $updatedData = ['quantity' => 15];
        $response = $this->putJson('/api/v1/sets/' . $set->id, $updatedData);
        $data = [
            'data' => [
                'id' => $set->id,
                'exercise_id' => $set->exercise_id,
                'workout_id' => $set->workout_id,
                'quantity' => $updatedData['quantity'],
                'time'=> $set->time,
                'distance' => $set->distance,
                'additional_weight' => $set->additional_weight,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
        $this->assertDatabaseHas('sets', $updatedData);
    }
    public function test_update_set_returns_a_not_found_response()
    {
        $set = Set::factory()->create();
        $updatedData = ['quantity' => 15];
        $response = $this->putJson('/api/v1/sets/' . $set->id + 1, $updatedData);
        $response->assertStatus(404);
    }
    public function test_update_set_invalid_url_returns_a_bad_request_response()
    {
        $updatedData = ['quantity' => 15];
        $response = $this->putJson('/api/v1/sets/f', $updatedData);
        $response->assertStatus(400);
    }
    public function test_update_set_invalid_value_returns_a_bad_request_response()
    {
        $set = Set::inRandomOrder()->first();
        $newSet = Set::factory()->create();
        $updatedData = ['quantity' => 'f'];
        $response = $this->putJson('/api/v1/sets/' . $newSet->id, $updatedData);
        $response->assertStatus(400);
    }
    public function test_update_set_references_id_does_not_exist_returns_a_bad_request_response()
    {
        $newSet = Set::factory()->create();
        $updatedData = ['exercise_id' => PHP_INT_MAX];
        $response = $this->putJson('/api/v1/sets/' . $newSet->id, $updatedData);
        $response->assertStatus(400);
    }

    public function test_patch_set_returns_a_successful_response()
    {
        $set = Set::factory()->create();
        $updatedData = ['quantity' => 15];
        $response = $this->patchJson('/api/v1/sets/' . $set->id, $updatedData);
        $data = [
            'data' => [
                'id' => $set->id,
                'exercise_id' => $set->exercise_id,
                'workout_id' => $set->workout_id,
                'quantity' => $updatedData['quantity'],
                'time'=> $set->time,
                'distance' => $set->distance,
                'additional_weight' => $set->additional_weight,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
        $this->assertDatabaseHas('sets', $updatedData);
    }
    public function test_patch_set_returns_a_not_found_response()
    {
        $set = Set::factory()->create();
        $updatedData = ['quantity' => 15];
        $response = $this->patchJson('/api/v1/sets/' . $set->id + 1, $updatedData);
        $response->assertStatus(404);
    }
    public function test_patch_set_invalid_url_returns_a_bad_request_response()
    {
        $updatedData = ['quantity' => 15];
        $response = $this->patchJson('/api/v1/sets/f', $updatedData);
        $response->assertStatus(400);
    }

    public function test_delete_set_returns_a_successful_response()
    {
        $set = Set::factory()->create();
        $response = $this->deleteJson('/api/v1/sets/' . $set->id);
        $data = [
            'data' => [
                'id' => $set['id'],
                'exercise_id' => $set['exercise_id'],
                'workout_id' => $set['workout_id'],
                'quantity' => $set['quantity'],
                'time'=> $set['time'],
                'distance' => $set['distance'],
                'additional_weight' => $set['additional_weight'],
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_delete_set_returns_a_not_found_response()
    {
        $set = Set::factory()->create();
        $response = $this->deleteJson('/api/v1/sets/' . $set->id + 1);
        $response->assertStatus(404);
    }
    public function test_delete_set_returns_a_bad_request_response()
    {
        $response = $this->deleteJson('/api/v1/sets/f');
        $response->assertStatus(400);
    }
}
