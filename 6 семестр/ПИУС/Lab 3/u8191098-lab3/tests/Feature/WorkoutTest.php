<?php

namespace Tests\Feature;

use App\Models\Workout;
use Tests\TestCase;

class WorkoutTest extends TestCase
{
    public function test_get_all_workouts_returns_a_successful_response()
    {
        $response = $this->get('/api/v1/workouts');

        $response->assertStatus(200);
    }
    public function test_get_workout_by_id_returns_a_successful_response()
    {
        $workout = Workout::factory()->create();
        $response = $this->get('/api/v1/workouts/' . $workout->id);

        $data = [
            'data' => [
                'id' => $workout->id,
                'date' => date_format($workout->date,'Y-m-d'),
                'duration' => $workout->duration,
                'calories' => $workout->calories,
                'max_puls'=> $workout->max_puls,
                'avg_puls' => $workout->avg_puls,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_get_workout_by_id_returns_a_bad_request_response()
    {
        $response = $this->get('/api/v1/workouts/f');
        $response->assertStatus(400);
    }
    public function test_get_workout_by_id_returns_a_not_found_response()
    {
        $workout = Workout::factory()->create();
        $response = $this->get('/api/v1/workouts/' . $workout->id + 1);
        $response->assertStatus(404);
    }

    public function test_create_workout_returns_a_successful_response()
    {
        $workout = Workout::factory()->raw();
        $response = $this->postJson('/api/v1/workouts/', $workout);
        $data = [
            'data' => [
                'date' => $workout['date'],
                'duration' => $workout['duration'],
                'calories' => $workout['calories'],
                'max_puls'=> $workout['max_puls'],
                'avg_puls' => $workout['avg_puls'],
            ],
        ];
        $response->assertStatus(201)->assertJson($data);
        $this->assertDatabaseHas('workouts', $workout);
    }

    public function test_update_workout_returns_a_successful_response()
    {
        $workout = Workout::factory()->create();
        $updatedData = ['duration' => 1555];
        $response = $this->putJson('/api/v1/workouts/' . $workout->id, $updatedData);
        $data = [
            'data' => [
                'id' => $workout->id,
                'date' => date_format($workout->date,'Y-m-d'),
                'duration' => $updatedData['duration'],
                'calories' => $workout->calories,
                'max_puls'=> $workout->max_puls,
                'avg_puls' => $workout->avg_puls,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
        $this->assertDatabaseHas('workouts', $updatedData);
    }
    public function test_update_workout_returns_a_not_found_response()
    {
        $workout = Workout::factory()->create();
        $updatedData = ['duration' => 1555];
        $response = $this->putJson('/api/v1/workouts/' . $workout->id + 1, $updatedData);
        $response->assertStatus(404);
    }
    public function test_update_workout_invalid_url_returns_a_bad_request_response()
    {
        $updatedData = ['duration' => 1555];
        $response = $this->putJson('/api/v1/workouts/f', $updatedData);
        $response->assertStatus(400);
    }

    public function test_patch_workout_returns_a_successful_response()
    {
        $workout = Workout::factory()->create();
        $updatedData = ['duration' => 1555];
        $response = $this->patchJson('/api/v1/workouts/' . $workout->id, $updatedData);
        $data = [
            'data' => [
                'id' => $workout->id,
                'date' => date_format($workout->date,'Y-m-d'),
                'duration' => $updatedData['duration'],
                'calories' => $workout->calories,
                'max_puls'=> $workout->max_puls,
                'avg_puls' => $workout->avg_puls,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
        $this->assertDatabaseHas('workouts', $updatedData);
    }
    public function test_patch_workout_returns_a_not_found_response()
    {
        $workout = Workout::factory()->create();
        $updatedData = ['duration' => 1555];
        $response = $this->patchJson('/api/v1/workouts/' . $workout->id + 1, $updatedData);
        $response->assertStatus(404);
    }
    public function test_patch_workout_invalid_url_returns_a_bad_request_response()
    {
        $updatedData = ['duration' => 1555];
        $response = $this->patchJson('/api/v1/workouts/f', $updatedData);
        $response->assertStatus(400);
    }

    public function test_delete_workout_returns_a_successful_response()
    {
        $workout = Workout::factory()->create();
        $response = $this->deleteJson('/api/v1/workouts/' . $workout->id);
        $data = [
            'data' => [
                'id' => $workout['id'],
                'date' => date_format($workout['date'],'Y-m-d'),
                'duration' => $workout['duration'],
                'calories' => $workout['calories'],
                'max_puls'=> $workout['max_puls'],
                'avg_puls' => $workout['avg_puls'],
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_delete_workout_returns_a_not_found_response()
    {
        $workout = Workout::factory()->create();
        $response = $this->deleteJson('/api/v1/workouts/' . $workout->id + 1);
        $response->assertStatus(404);
    }
    public function test_delete_workout_returns_a_bad_request_response()
    {
        $response = $this->deleteJson('/api/v1/workouts/f');
        $response->assertStatus(400);
    }
}
