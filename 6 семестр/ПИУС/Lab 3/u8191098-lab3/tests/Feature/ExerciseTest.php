<?php

namespace Tests\Feature;

use App\Models\Exercise;
use Tests\TestCase;

class ExerciseTest extends TestCase
{
    public function test_get_all_exercises_returns_a_successful_response()
    {
        $response = $this->get('/api/v1/exercises');

        $response->assertStatus(200);
    }
    public function test_get_exercise_by_id_returns_a_successful_response()
    {
        $exercise = Exercise::factory()->create();
        $response = $this->get('/api/v1/exercises/' . $exercise->id);

        $data = [
            'data' => [
                'id' => $exercise->id,
                'name' => $exercise->name,
                'exercise_type_id' => $exercise->exercise_type_id,
                'muscle_group_id' => $exercise->muscle_group_id,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_get_exercise_by_id_returns_a_bad_request_response()
    {
        $response = $this->get('/api/v1/exercises/f');
        $response->assertStatus(400);
    }
    public function test_get_exercise_by_id_returns_a_not_found_response()
    {
        $exercise = Exercise::factory()->create();
        $response = $this->get('/api/v1/exercises/' . $exercise->id + 1);
        $response->assertStatus(404);
    }

    public function test_create_exercise_returns_a_successful_response()
    {
        $exercise = Exercise::factory()->raw();
        $response = $this->postJson('/api/v1/exercises/', $exercise);
        $data = [
            'data' => [
                'name' => $exercise['name'],
                'exercise_type_id' => $exercise['exercise_type_id'],
                'muscle_group_id' => $exercise['muscle_group_id'],
            ],
        ];
        $response->assertStatus(201)->assertJson($data);
        $this->assertDatabaseHas('exercises', $exercise);
    }
    public function test_create_exercise_returns_a_bad_request_response()
    {
        $exercise = Exercise::factory()->raw();
        $this->postJson('/api/v1/exercises/', $exercise);

        $response = $this->postJson('/api/v1/exercises/', $exercise);
        $response->assertStatus(400);
    }

    public function test_update_exercise_returns_a_successful_response()
    {
        $exercise = Exercise::factory()->create();
        $updatedData = ['name' => 'Updated Name ' . $exercise->id + 1];
        $response = $this->putJson('/api/v1/exercises/' . $exercise->id, $updatedData);
        $data = [
            'data' => [
                'id' => $exercise->id,
                'name' => $updatedData['name'],
                'exercise_type_id' => $exercise->exercise_type_id,
                'muscle_group_id' => $exercise->muscle_group_id,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
        $this->assertDatabaseHas('exercises', $updatedData);
    }
    public function test_update_exercise_returns_a_not_found_response()
    {
        $exercise = Exercise::factory()->create();
        $updatedData = ['name' => 'Updated Name ' . $exercise->id + 1];
        $response = $this->putJson('/api/v1/exercises/' . $exercise->id + 1, $updatedData);
        $response->assertStatus(404);
    }
    public function test_update_exercise_invalid_url_returns_a_bad_request_response()
    {
        $updatedData = ['name' => 'Updated Name'];
        $response = $this->putJson('/api/v1/exercises/f', $updatedData);
        $response->assertStatus(400);
    }
    public function test_update_exercise_not_unique_name_returns_a_bad_request_response()
    {
        $exercise = Exercise::inRandomOrder()->first();
        $newExercise = Exercise::factory()->create();
        $updatedData = ['name' => $exercise->name];
        $response = $this->putJson('/api/v1/exercises/' . $newExercise->id, $updatedData);
        $response->assertStatus(400);
    }
    public function test_update_exercise_references_id_does_not_exist_returns_a_bad_request_response()
    {
        $newExercise = Exercise::factory()->create();
        $updatedData = ['exercise_type_id' => PHP_INT_MAX];
        $response = $this->putJson('/api/v1/exercises/' . $newExercise->id, $updatedData);
        $response->assertStatus(400);
    }

    public function test_patch_exercise_returns_a_successful_response()
    {
        $exercise = Exercise::factory()->create();
        $updatedData = ['name' => 'Updated Name ' . $exercise->id + 1];
        $response = $this->patchJson('/api/v1/exercises/' . $exercise->id, $updatedData);
        $data = [
            'data' => [
                'id' => $exercise->id,
                'name' => $updatedData['name'],
                'exercise_type_id' => $exercise->exercise_type_id,
                'muscle_group_id' => $exercise->muscle_group_id,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
        $this->assertDatabaseHas('exercises', $updatedData);
    }
    public function test_patch_exercise_returns_a_not_found_response()
    {
        $exercise = Exercise::factory()->create();
        $updatedData = ['name' => 'Updated Name ' . $exercise->id + 1];
        $response = $this->patchJson('/api/v1/exercises/' . $exercise->id + 1, $updatedData);
        $response->assertStatus(404);
    }
    public function test_patch_exercise_invalid_url_returns_a_bad_request_response()
    {
        $updatedData = ['name' => 'Updated Name'];
        $response = $this->patchJson('/api/v1/exercises/f', $updatedData);
        $response->assertStatus(400);
    }
    public function test_patch_exercise_not_unique_name_returns_a_bad_request_response()
    {
        $exercise = Exercise::inRandomOrder()->first();
        $newExercise = Exercise::factory()->create();
        $updatedData = ['name' => $exercise->name];
        $response = $this->patchJson('/api/v1/exercises/' . $newExercise->id, $updatedData);
        $response->assertStatus(400);
    }

    public function test_delete_exercise_returns_a_successful_response()
    {
        $exercise = Exercise::factory()->create();
        $response = $this->deleteJson('/api/v1/exercises/' . $exercise->id);
        $data = [
            'data' => [
                'id' => $exercise['id'],
                'name' => $exercise['name'],
                'exercise_type_id' => $exercise['exercise_type_id'],
                'muscle_group_id' => $exercise['muscle_group_id'],
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_delete_exercise_returns_a_not_found_response()
    {
        $exercise = Exercise::factory()->create();
        $response = $this->deleteJson('/api/v1/exercises/' . $exercise->id + 1);
        $response->assertStatus(404);
    }
    public function test_delete_exercise_returns_a_bad_request_response()
    {
        $response = $this->deleteJson('/api/v1/exercises/f');
        $response->assertStatus(400);
    }
}
