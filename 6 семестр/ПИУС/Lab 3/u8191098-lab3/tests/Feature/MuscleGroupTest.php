<?php

namespace Tests\Feature;

use App\Models\MuscleGroup;
use Tests\TestCase;

class MuscleGroupTest extends TestCase
{
    public function test_get_all_muscle_groups_returns_a_successful_response()
    {
        $response = $this->get('/api/v1/muscle-groups');

        $response->assertStatus(200);
    }
    public function test_get_muscle_group_by_id_returns_a_successful_response()
    {
        $muscleGroup = MuscleGroup::factory()->create();
        $response = $this->get('/api/v1/muscle-groups/' . $muscleGroup->id);

        $data = [
            'data' => [
                'id' => $muscleGroup->id,
                'name' => $muscleGroup->name,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_get_muscle_group_by_id_returns_a_bad_request_response()
    {
        $response = $this->get('/api/v1/muscle-groups/f');
        $response->assertStatus(400);
    }
    public function test_get_muscle_group_by_id_returns_a_not_found_response()
    {
        $muscleGroup = MuscleGroup::factory()->create();
        $response = $this->get('/api/v1/muscle-groups/' . $muscleGroup->id + 1);
        $response->assertStatus(404);
    }

    public function test_create_muscle_group_returns_a_successful_response()
    {
        $muscleGroup = MuscleGroup::factory()->raw();
        $response = $this->postJson('/api/v1/muscle-groups/', $muscleGroup);
        $data = [
            'data' => [
                'name' => $muscleGroup['name'],
            ],
        ];
        $response->assertStatus(201)->assertJson($data);
        $this->assertDatabaseHas('muscle_groups', $muscleGroup);
    }
    public function test_create_muscle_group_returns_a_bad_request_response()
    {
        $muscleGroup = MuscleGroup::factory()->raw();
        $this->postJson('/api/v1/muscle-groups/', $muscleGroup);

        $response = $this->postJson('/api/v1/muscle-groups/', $muscleGroup);
        $response->assertStatus(400);
    }

    public function test_update_muscle_group_returns_a_successful_response()
    {
        $muscleGroup = MuscleGroup::factory()->create();
        $updatedData = ['name' => 'Updated Name ' . $muscleGroup->id + 1];
        $response = $this->putJson('/api/v1/muscle-groups/' . $muscleGroup->id, $updatedData);
        $data = [
            'data' => [
                'id' => $muscleGroup->id,
                'name' => $updatedData['name'],
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
        $this->assertDatabaseHas('muscle_groups', $updatedData);
    }
    public function test_update_muscle_group_returns_a_not_found_response()
    {
        $muscleGroup = MuscleGroup::factory()->create();
        $updatedData = ['name' => 'Updated Name ' . $muscleGroup->id + 1];
        $response = $this->putJson('/api/v1/muscle-groups/' . $muscleGroup->id + 1, $updatedData);
        $response->assertStatus(404);
    }
    public function test_update_muscle_group_invalid_url_returns_a_bad_request_response()
    {
        $updatedData = ['name' => 'Updated Name'];
        $response = $this->putJson('/api/v1/muscle-groups/f', $updatedData);
        $response->assertStatus(400);
    }
    public function test_update_muscle_group_not_unique_name_returns_a_bad_request_response()
    {
        $muscleGroup = MuscleGroup::inRandomOrder()->first();
        $newMuscleGroup = MuscleGroup::factory()->create();
        $updatedData = ['name' => $muscleGroup->name];
        $response = $this->putJson('/api/v1/muscle-groups/' . $newMuscleGroup->id, $updatedData);
        $response->assertStatus(400);
    }

    public function test_delete_muscle_group_returns_a_successful_response()
    {
        $muscleGroup = MuscleGroup::factory()->create();
        $response = $this->deleteJson('/api/v1/muscle-groups/' . $muscleGroup->id);
        $data = [
            'data' => [
                'id' => $muscleGroup['id'],
                'name' => $muscleGroup['name'],
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_delete_muscle_group_returns_a_not_found_response()
    {
        $muscleGroup = MuscleGroup::factory()->create();
        $response = $this->deleteJson('/api/v1/muscle-groups/' . $muscleGroup->id + 1);
        $response->assertStatus(404);
    }
    public function test_delete_muscle_group_returns_a_bad_request_response()
    {
        $response = $this->deleteJson('/api/v1/muscle-groups/f');
        $response->assertStatus(400);
    }
}
